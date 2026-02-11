do_pragma_once (cpp_reader *pfile)
{
  if (pfile->buffer->prev == NULL)
    cpp_error (pfile, CPP_DL_WARNING, "#pragma once in main file");

  check_eol (pfile);
  _cpp_mark_file_once_only (pfile, pfile->buffer->file);
}
