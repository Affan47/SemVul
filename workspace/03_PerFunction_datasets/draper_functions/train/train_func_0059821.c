ConvertToNative(const std::string& raw,
                                   const std::string& target,
                                   uint64_t skip, uint64_t component_size,
                                   uint64_t n_components, bool is_signed,
                                   bool fp, UINT64VECTOR3 dimensions,
                                   FLOATVECTOR3 aspect, bool batch,
                                   const bool bQuantizeTo8Bit)
{
  std::string fn_data = SysTools::RemoveExt(target);

  std::ofstream header(target.c_str(), std::ios::out | std::ios::trunc);

  std::string data_format;
  switch(component_size) {
    case 8: data_format = "BYTE"; break;
    case 16: data_format = "SHORT"; break;
    case 32:
      if(fp) { data_format = "FLOAT"; }
      else   { data_format = "INT"; }
      break;
    case 64:


      if(fp) { data_format = "DOUBLE"; }
      else   { data_format = "INT"; }
      break;
  }
  header << "DATA_FILE: " << raw << ".data" << std::endl
         << "DATA SIZE: "
            << dimensions[0] << " " << dimensions[1] << " " << dimensions[2]
         << std::endl
         << "DATA FORMAT: " << data_format << std::endl
         << "DATA_COMPONENTS: " << n_components << std::endl
         << "VARIABLE: from_imagevis3d" << std::endl
         << "BRICK_SIZE: "
            << dimensions[0] << " " << dimensions[1] << " " << dimensions[2]
         << std::endl
         << "CENTERING: nodal" << std::endl;
  header.close();


  return RAWConverter::ConvertToNative(raw, raw + ".data", skip,
                                       component_size, n_components, is_signed,
                                       fp, dimensions, aspect, batch,
                                       bQuantizeTo8Bit);
}
