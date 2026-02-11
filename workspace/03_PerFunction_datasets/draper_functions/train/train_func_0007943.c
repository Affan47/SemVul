HEreport(const char *format,...)
{
    va_list     arg_ptr;
    char       *tmp;
    CONSTR(FUNC, "HEreport");

    va_start(arg_ptr, format);

    if ((error_top < ERR_STACK_SZ + 1) && (error_top > 0))
      {
          tmp = (char *) HDmalloc(ERR_STRING_SIZE);
          if (!tmp)
            {
                HERROR(DFE_NOSPACE);
                goto done;
            }
          vsprintf(tmp, format, arg_ptr);
          if (error_stack[error_top - 1].desc)
              HDfree(error_stack[error_top - 1].desc);
          error_stack[error_top - 1].desc = tmp;
      }

    va_end(arg_ptr);

done:
    return;
}
