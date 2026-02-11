getLSDAEncoding() const {
  CodeModel::Model Model = TM.getCodeModel();
  if (TM.getRelocationModel() == Reloc::PIC_)
    return DW_EH_PE_pcrel | (Model == CodeModel::Small ?
                             DW_EH_PE_sdata4 : DW_EH_PE_sdata8);

  if (Model == CodeModel::Small)
    return DW_EH_PE_udata4;

  return DW_EH_PE_absptr;
}
