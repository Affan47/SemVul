_mesa_get_srgb_format_linear(mesa_format format)
{
   switch (format) {
   case MESA_FORMAT_BGR_SRGB8:
      format = MESA_FORMAT_BGR_UNORM8;
      break;
   case MESA_FORMAT_A8B8G8R8_SRGB:
      format = MESA_FORMAT_A8B8G8R8_UNORM;
      break;
   case MESA_FORMAT_B8G8R8A8_SRGB:
      format = MESA_FORMAT_B8G8R8A8_UNORM;
      break;
   case MESA_FORMAT_L_SRGB8:
      format = MESA_FORMAT_L_UNORM8;
      break;
   case MESA_FORMAT_L8A8_SRGB:
      format = MESA_FORMAT_L8A8_UNORM;
      break;
   case MESA_FORMAT_SRGB_DXT1:
      format = MESA_FORMAT_RGB_DXT1;
      break;
   case MESA_FORMAT_SRGBA_DXT1:
      format = MESA_FORMAT_RGBA_DXT1;
      break;
   case MESA_FORMAT_SRGBA_DXT3:
      format = MESA_FORMAT_RGBA_DXT3;
      break;
   case MESA_FORMAT_SRGBA_DXT5:
      format = MESA_FORMAT_RGBA_DXT5;
      break;
   case MESA_FORMAT_R8G8B8X8_SRGB:
      format = MESA_FORMAT_R8G8B8X8_UNORM;
      break;
   case MESA_FORMAT_ETC2_SRGB8:
      format = MESA_FORMAT_ETC2_RGB8;
      break;
   case MESA_FORMAT_ETC2_SRGB8_ALPHA8_EAC:
      format = MESA_FORMAT_ETC2_RGBA8_EAC;
      break;
   case MESA_FORMAT_ETC2_SRGB8_PUNCHTHROUGH_ALPHA1:
      format = MESA_FORMAT_ETC2_RGB8_PUNCHTHROUGH_ALPHA1;
      break;
   default:
      break;
   }
   return format;
}
