Initialize(std::string params_file)
  {
    std::ifstream is;
    if (params_file != "") {
      try {
        is.open(params_file.c_str());
      }
      catch (std::bad_alloc&) {
        jnlst_->Printf(J_SUMMARY, J_MAIN, "\nEXIT: Not enough memory.\n");
        return Insufficient_Memory;
      }
      catch (...) {
        IpoptException exc("Unknown Exception caught in ipopt", "Unknown File", -1);
        exc.ReportException(*jnlst_);
        return NonIpopt_Exception_Thrown;
      }
    }
    ApplicationReturnStatus retval = Initialize(is);
    if (is) {
      is.close();
    }
    return retval;
  }
