particulate_field_event (GfsEvent * event,
					 GfsSimulation * sim)
{
  if ((* GFS_EVENT_CLASS (GTS_OBJECT_CLASS (gfs_particulate_field_class ())->parent_class)->event)
      (event, sim)) {
    GfsDomain * domain = GFS_DOMAIN (sim);
    GfsVariable * v = GFS_VARIABLE1 (event);
    GfsParticulateField * pfield = GFS_PARTICULATE_FIELD (v);


    gfs_domain_cell_traverse (domain, FTT_PRE_ORDER, FTT_TRAVERSE_LEAFS, -1,
			      (FttCellTraverseFunc) gfs_cell_reset, v);

    GSList * i = GFS_EVENT_LIST (pfield->plist)->list->items;
    while (i) {
      FttCell * cellpart = gfs_domain_locate (domain, GFS_PARTICLE (i->data)->pos, -1, NULL);
      if (cellpart)
	pfield->voidfraction_func (cellpart, v, i->data);
      i = i->next;
    }
    return TRUE;
  }
  return FALSE;
}
