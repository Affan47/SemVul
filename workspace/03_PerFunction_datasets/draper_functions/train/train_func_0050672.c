xsh_mode_tostring(XSH_MODE mode){
  return
    (mode == XSH_MODE_IFU) ? "IFU" :
    (mode == XSH_MODE_SLIT) ? "SLIT" : "UNDEFINED";
}
