_eglMatchConfig(const _EGLConfig *conf, const _EGLConfig *criteria)
{
   EGLint attr, val, i;
   EGLBoolean matched = EGL_TRUE;

   for (i = 0; i < ARRAY_SIZE(_eglValidationTable); i++) {
      EGLint cmp;
      if (_eglValidationTable[i].criterion == ATTRIB_CRITERION_IGNORE)
         continue;

      attr = _eglValidationTable[i].attr;
      cmp = _eglGetConfigKey(criteria, attr);
      if (cmp == EGL_DONT_CARE)
         continue;

      val = _eglGetConfigKey(conf, attr);
      switch (_eglValidationTable[i].criterion) {
      case ATTRIB_CRITERION_EXACT:
         if (val != cmp)
            matched = EGL_FALSE;
         break;
      case ATTRIB_CRITERION_ATLEAST:
         if (val < cmp)
            matched = EGL_FALSE;
         break;
      case ATTRIB_CRITERION_MASK:
         if ((val & cmp) != cmp)
            matched = EGL_FALSE;
         break;
      case ATTRIB_CRITERION_SPECIAL:

         break;
      default:
         assert(0);
         break;
      }

      if (!matched) {
#ifndef DEBUG

         if (attr != EGL_RENDERABLE_TYPE)
            break;
#endif
         _eglLog(_EGL_DEBUG,
               "the value (0x%x) of attribute 0x%04x did not meet the criteria (0x%x)",
               val, attr, cmp);
         break;
      }
   }

   return matched;
}
