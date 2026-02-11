getArchivingPath(bool car)
  {

    if ((*this)["jobreport_option_archiving"].empty()) return std::string();


    std::string base_fn;
    size_type seppos=filename.rfind('/');
    if (seppos==std::string::npos)
      base_fn=filename;
    else
      base_fn=filename.substr(seppos+1,std::string::npos);

    if (car) {
      return (*this)["jobreport_option_archiving"]+"/usagerecordCAR."+base_fn;
    }
    return (*this)["jobreport_option_archiving"]+"/usagerecord."+base_fn;
  }

}
