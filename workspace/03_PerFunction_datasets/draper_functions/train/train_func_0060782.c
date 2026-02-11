getFullfilename(const t_canvas*canvas, const char*filename, const char*ext) {
    std::string fullname_;

    char buf[MAXPDSTRING];
    char*bufptr;
    int fd=0;
    if ((fd=canvas_open(const_cast<t_canvas*>(canvas), filename, ext, buf, &bufptr, MAXPDSTRING, 1))>=0){
      ::close(fd);
      fullname_=buf;
      fullname_+="/";
      fullname_+=bufptr;
    } else {
      if(canvas) {
        canvas_makefilename(const_cast<t_canvas*>(canvas), const_cast<char*>(filename), buf, MAXPDSTRING);
        fullname_=buf;
      } else {
        return std::string("");
      }
    }
    return fullname_;
  }
