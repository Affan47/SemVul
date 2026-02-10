component(int what)
{
    switch (what) {
      case D_CLASS:		return &name;
      case D_CXX_CLASS:		return &cxx;
      case D_HEADER_FILE:	return &header_file;
      case D_SOURCE_FILE:	return &source_file;
      case D_PORT_COUNT:	return &port_count_code;
      case D_PROCESSING:	return &processing_code;
      case D_FLOW_CODE:		return &flow_code;
      case D_FLAGS:		return &flags;
      case D_METHODS:		return &methods;
      case D_REQUIREMENTS:	return &requirements;
      case D_PROVISIONS:	return &provisions;
      case D_LIBS:		return &libs;
      case D_DOC_NAME:		return &documentation_name;
      default:			return 0;
    }
}
