mlxsw_emad_pack_op_tlv(char *op_tlv,
				   const struct mlxsw_reg_info *reg,
				   enum mlxsw_core_reg_access_type type,
				   struct mlxsw_core *mlxsw_core)
{
	mlxsw_emad_op_tlv_type_set(op_tlv, MLXSW_EMAD_TLV_TYPE_OP);
	mlxsw_emad_op_tlv_len_set(op_tlv, MLXSW_EMAD_OP_TLV_LEN);
	mlxsw_emad_op_tlv_dr_set(op_tlv, 0);
	mlxsw_emad_op_tlv_status_set(op_tlv, 0);
	mlxsw_emad_op_tlv_register_id_set(op_tlv, reg->id);
	mlxsw_emad_op_tlv_r_set(op_tlv, MLXSW_EMAD_OP_TLV_REQUEST);
	if (type == MLXSW_CORE_REG_ACCESS_TYPE_QUERY)
		mlxsw_emad_op_tlv_method_set(op_tlv,
					     MLXSW_EMAD_OP_TLV_METHOD_QUERY);
	else
		mlxsw_emad_op_tlv_method_set(op_tlv,
					     MLXSW_EMAD_OP_TLV_METHOD_WRITE);
	mlxsw_emad_op_tlv_class_set(op_tlv,
				    MLXSW_EMAD_OP_TLV_CLASS_REG_ACCESS);
	mlxsw_emad_op_tlv_tid_set(op_tlv, mlxsw_core->emad.tid);
}
