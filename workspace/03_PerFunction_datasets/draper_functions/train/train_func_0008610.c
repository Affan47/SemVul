open(const std::string filename, const gem::Properties&wantProps)
{
  int wantedFormat=GL_RGBA;
  double d;
  unsigned int format=0;
  if(wantProps.get("format", d)) {
    format=d;
  }
  switch(format){
  default:
    break;
  case GL_RGBA:
  case GL_YCBCR_422_GEM:
  case GL_LUMINANCE:
    m_wantedFormat=format;
    break;
  }

  char*cfilename=const_cast<char*>(filename.c_str());
  if (quicktime_check_sig(cfilename)){
    if (!(m_quickfile = quicktime_open(filename.c_str(), 1, 0))){

      return false;
    }
    m_curFrame = -1;


    m_numTracks = quicktime_video_tracks(m_quickfile);

    m_numFrames = quicktime_video_length(m_quickfile, m_curTrack) - 1;

    m_fps = quicktime_frame_rate(m_quickfile, m_curTrack);

    m_image.image.xsize = quicktime_video_width (m_quickfile, m_curTrack);
    m_image.image.ysize = quicktime_video_height(m_quickfile, m_curTrack);
    if (!quicktime_supported_video(m_quickfile, m_curTrack)){


      quicktime_close(m_quickfile);
      m_quickfile=0;
      return false;
    }
    m_image.image.setCsizeByFormat(wantedFormat);
    m_image.image.reallocate();

    m_qtimage.xsize=m_image.image.xsize;
    m_qtimage.ysize=m_image.image.ysize;
    m_qtimage.setCsizeByFormat(GL_RGB);
    m_qtimage.reallocate();

    m_newfilm = true;
   return true;
  }
  goto unsupported;
 unsupported:
  close();
  return false;
}
