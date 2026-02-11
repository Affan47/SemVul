draw_module_declarations(ivl_design_t des)
{
      const char*cp = ivl_design_flag(des, "VPI_MODULE_LIST");

      while (*cp) {
	    char buffer[128];
	    const char*comma = strchr(cp, ',');

	    if (comma == 0)
		  comma = cp + strlen(cp);

	    strncpy(buffer, cp, comma-cp);
	    buffer[comma-cp] = 0;
	    fprintf(vvp_out, ":vpi_module \"%s\";\n", buffer);

	    cp = comma;
	    if (*cp) cp += 1;
      }
}
