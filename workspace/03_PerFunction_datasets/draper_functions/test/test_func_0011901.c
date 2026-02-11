fiasco_c_options_set_progress_meter (fiasco_c_options_t *options,
				     fiasco_progress_e type)


{
   c_options_t *this = (c_options_t *) cast_c_options (options);

   if (!this)
   {
      return 0;
   }
   switch (type)
   {
      case FIASCO_PROGRESS_BAR:
      case FIASCO_PROGRESS_PERCENT:
      case FIASCO_PROGRESS_NONE:
	 this->progress_meter = type;
	 break;
      default:
	 set_error (_("Invalid progress meter `%d' specified "
		      "(valid values are 0, 1, or 2)."), type);
	 return 0;
   }
   return 1;
}
