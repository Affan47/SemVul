load_libexpat ()
{
  if (libexpat_loaded == 0)
    {
      void *handle;


      handle = dlopen ("libexpat.so.1", RTLD_LAZY);
      if (handle == NULL)

        handle = dlopen ("libexpat.so.0", RTLD_LAZY);
      if (handle != NULL
          && (p_XML_ExpatVersionInfo =
                (XML_Expat_Version (*) (void))
                dlsym (handle, "XML_ExpatVersionInfo")) != NULL
          && (p_XML_GetFeatureList =
                (const XML_Feature * (*) (void))
                dlsym (handle, "XML_GetFeatureList")) != NULL
          && (p_XML_ParserCreate =
                (XML_Parser (*) (const XML_Char *))
                dlsym (handle, "XML_ParserCreate")) != NULL
          && (p_XML_SetElementHandler =
                (void (*) (XML_Parser, XML_StartElementHandler, XML_EndElementHandler))
                dlsym (handle, "XML_SetElementHandler")) != NULL
          && (p_XML_SetCharacterDataHandler =
                (void (*) (XML_Parser, XML_CharacterDataHandler))
                dlsym (handle, "XML_SetCharacterDataHandler")) != NULL
          && (p_XML_SetCommentHandler =
                (void (*) (XML_Parser, XML_CommentHandler))
                dlsym (handle, "XML_SetCommentHandler")) != NULL
          && (p_XML_Parse =
                (int (*) (XML_Parser, const char *, int, int))
                dlsym (handle, "XML_Parse")) != NULL
          && (p_XML_GetErrorCode =
                (enum XML_Error (*) (XML_Parser))
                dlsym (handle, "XML_GetErrorCode")) != NULL
          && (p_XML_GetCurrentLineNumber =
                dlsym (handle, "XML_GetCurrentLineNumber")) != NULL
          && (p_XML_GetCurrentColumnNumber =
                dlsym (handle, "XML_GetCurrentColumnNumber")) != NULL
          && (p_XML_ParserFree =
                (void (*) (XML_Parser))
                dlsym (handle, "XML_ParserFree")) != NULL
          && (p_XML_ErrorString =
                (const XML_LChar * (*) (int))
                dlsym (handle, "XML_ErrorString")) != NULL)
        libexpat_loaded = 1;
      else
        libexpat_loaded = -1;
    }
  return libexpat_loaded >= 0;
}
