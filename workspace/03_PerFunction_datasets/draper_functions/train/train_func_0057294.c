vrrp_init_state(list l)
{
	vrrp_t *vrrp;
	vrrp_sgroup_t *vgroup;
	element e;

	for (e = LIST_HEAD(l); e; ELEMENT_NEXT(e)) {
		vrrp = ELEMENT_DATA(e);


		if (vrrp->sync && !vrrp->sync->global_tracking) {
			element e2;
			tracked_sc_t *sc;
			tracked_if_t *tip;
			int warning = 0;

			if (!LIST_ISEMPTY(vrrp->track_ifp)) {
				for (e2 = LIST_HEAD(vrrp->track_ifp); e2; ELEMENT_NEXT(e2)) {
					tip = ELEMENT_DATA(e2);
					if (tip->weight) {
						tip->weight = 0;
						warning++;
					}
				}
			}

			if (!LIST_ISEMPTY(vrrp->track_script)) {
				for (e2 = LIST_HEAD(vrrp->track_script); e2; ELEMENT_NEXT(e2)) {
					sc = ELEMENT_DATA(e2);
					if (sc->weight) {
						sc->scr->inuse--;
						warning++;
					}
				}
			}

			if (warning > 0) {
				log_message(LOG_INFO, "VRRP_Instance(%s) : ignoring "
						 "tracked script with weights due to SYNC group",
				       vrrp->iname);
			}
		} else {

			thread_add_timer(master, vrrp_update_priority,
					 vrrp, vrrp->adver_int);
		}

		if (vrrp->base_priority == VRRP_PRIO_OWNER ||
		    vrrp->wantstate == VRRP_STATE_MAST) {
#ifdef _HAVE_IPVS_SYNCD_

			if (vrrp->lvs_syncd_if)
				ipvs_syncd_cmd(IPVS_STARTDAEMON,
					       vrrp->lvs_syncd_if, IPVS_MASTER,
					       vrrp->vrid);
#endif
			vrrp->state = VRRP_STATE_GOTO_MASTER;
		} else {
			vrrp->ms_down_timer = 3 * vrrp->adver_int
			    + VRRP_TIMER_SKEW(vrrp);
#ifdef _HAVE_IPVS_SYNCD_

			if (vrrp->lvs_syncd_if)
				ipvs_syncd_cmd(IPVS_STARTDAEMON,
					       vrrp->lvs_syncd_if, IPVS_BACKUP,
					       vrrp->vrid);
#endif
			log_message(LOG_INFO, "VRRP_Instance(%s) Entering BACKUP STATE",
			       vrrp->iname);


			vrrp_restore_interface(vrrp, 0);
			vrrp->state = VRRP_STATE_BACK;
			vrrp_smtp_notifier(vrrp);
			notify_instance_exec(vrrp, VRRP_STATE_BACK);
#ifdef _WITH_SNMP_
			vrrp_snmp_instance_trap(vrrp);
#endif


			if ((vgroup = vrrp->sync)) {
				if (GROUP_STATE(vgroup) != VRRP_STATE_BACK) {
					vgroup->state = VRRP_STATE_BACK;
					vrrp_sync_smtp_notifier(vgroup);
					notify_group_exec(vgroup, VRRP_STATE_BACK);
#ifdef _WITH_SNMP_
					vrrp_snmp_group_trap(vgroup);
#endif
				}
			}
		}
	}
}
