get_start_param(Octstr *content_type)
{
     Octstr *start;
     int len;

     if (!content_type)
	  return NULL;

     start = http_get_header_parameter(content_type, octstr_imm("start"));
     if (start && (len = octstr_len(start)) > 0 &&
	 octstr_get_char(start, 0) == '"' && octstr_get_char(start, len-1) == '"') {
	  octstr_delete(start, 0, 1);
	  octstr_delete(start, len-2, 1);
     }

     return start;
}
