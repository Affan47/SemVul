poldiff_stats_t_get_stat(poldiff_stats_t *self,poldiff_form_e form){
		BEGIN_EXCEPTION
		switch(form) {
			case POLDIFF_FORM_ADDED:
			{
				return self->stats[0];
			}
			case POLDIFF_FORM_REMOVED:
			{
				return self->stats[1];
			}
			case POLDIFF_FORM_MODIFIED:
			{
				return self->stats[2];
			}
			case POLDIFF_FORM_ADD_TYPE:
			{
				return self->stats[3];
			}
			case POLDIFF_FORM_REMOVE_TYPE:
			{
				return self->stats[4];
			}
			case POLDIFF_FORM_NONE:
			default:
			{
				{SWIG_JavaException(local_jenv, SWIG_ValueError, "Invalid poldiff form"); goto fail;};
			}
		}
		END_EXCEPTION
	fail:
		return 0;
	}
