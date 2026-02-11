createFreeTypeFont(const String& font_name,
                                      const float point_size,
                                      const bool anti_aliased,
                                      const String& font_filename,
                                      const String& resource_group,
                                      const bool auto_scaled,
                                      const float native_horz_res,
                                      const float native_vert_res,
                                      XMLResourceExistsAction action)
{
#ifdef CEGUI_HAS_FREETYPE
    Logger::getSingleton().logEvent("Attempting to create FreeType font '" +
        font_name + "' using font file '" + font_filename + "'.");


    Font* object = new FreeTypeFont(font_name, point_size, anti_aliased,
                                    font_filename, resource_group, auto_scaled,
                                    native_horz_res, native_vert_res);


    return doExistingObjectAction(font_name, object, action);

#else
    CEGUI_THROW(InvalidRequestException("FontManager::createFreeTypeFont: "
        "CEGUI was compiled without freetype support."));
#endif
}
