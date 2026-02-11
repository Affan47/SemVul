CanReadFile(const std::string& filename)
  {
    Open3DMotion::MotionFileHandler handler("Biomechanical ToolKit", BTK_VERSION_STRING);
    Open3DMotion::TreeValue* readoptions = NULL;
    std::ifstream ifs(filename.c_str(), std::ios::binary);
    Open3DMotion::FileFormatXMove ff;
    return (ifs.is_open() && ff.Probe(handler, readoptions, ifs));
  }
