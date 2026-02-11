i40e_vc_vf_broadcast(struct i40e_pf *pf,
				 enum i40e_virtchnl_ops v_opcode,
				 i40e_status v_retval, u8 *msg,
				 u16 msglen)
{
	struct i40e_hw *hw = &pf->hw;
	struct i40e_vf *vf = pf->vf;
	int i;

	for (i = 0; i < pf->num_alloc_vfs; i++, vf++) {
		int abs_vf_id = vf->vf_id + hw->func_caps.vf_base_id;

		if (!test_bit(I40E_VF_STAT_INIT, &vf->vf_states) &&
		    !test_bit(I40E_VF_STAT_ACTIVE, &vf->vf_states))
			continue;


		i40e_aq_send_msg_to_vf(hw, abs_vf_id, v_opcode, v_retval,
				       msg, msglen, NULL);
	}
}
