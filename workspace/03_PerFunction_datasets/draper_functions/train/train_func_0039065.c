next_runtime_abi_01_init_metadata_attributes (void)
{
  if (!objc_meta)
    objc_meta = get_identifier ("OBJC1META");

  if (!meta_base)
    meta_base = get_identifier ("V1_BASE");

  meta_class = get_identifier ("V1_CLAS");
  meta_metaclass = get_identifier ("V1_META");
  meta_category = get_identifier ("V1_CATG");
  meta_protocol = get_identifier ("V1_PROT");

  meta_clac_vars = get_identifier ("V1_CLCV");
  meta_clai_vars = get_identifier ("V1_CLIV");

  meta_clac_meth = get_identifier ("V1_CLCM");
  meta_clai_meth = get_identifier ("V1_CLIM");
  meta_catc_meth = get_identifier ("V1_CACM");
  meta_cati_meth = get_identifier ("V1_CAIM");
  meta_proto_cls_meth = get_identifier ("V1_PCLM");
  meta_proto_nst_meth = get_identifier ("V1_PNSM");

  meta_clas_prot = get_identifier ("V1_CLPR");
  meta_catg_prot = get_identifier ("V1_CAPR");

  meta_class_reference = get_identifier ("V1_CLRF");
  meta_proto_ref = get_identifier ("V1_PRFS");
  meta_sel_refs = get_identifier ("V1_SRFS");

  meta_class_name = get_identifier ("V1_CLSN");
  meta_meth_name = get_identifier ("V1_METN");
  meta_meth_type = get_identifier ("V1_METT");
  meta_prop_name_attr = get_identifier ("V1_STRG");

  meta_modules = get_identifier ("V1_MODU");
  meta_symtab = get_identifier ("V1_SYMT");
  meta_info = get_identifier ("V1_INFO");

  meta_proplist = get_identifier ("V1_PLST");
  meta_protocol_extension = get_identifier ("V1_PEXT");
  meta_class_extension = get_identifier ("V1_CEXT");

  meta_const_str = get_identifier ("V1_CSTR");
}
