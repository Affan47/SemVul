genie_write_file (NODE_T * p)
{
  A68_REF ref_file;
  A68_FILE *file;
  A68_REF row;
  A68_ARRAY *arr;
  A68_TUPLE *tup;
  BYTE_T *base_address;
  int elems, k, elem_index;
  POP_REF (p, &row);
  CHECK_REF (p, row, MODE (ROW_SIMPLOUT));
  GET_DESCRIPTOR (arr, tup, &row);
  elems = ROW_SIZE (tup);
  POP_REF (p, &ref_file);
  CHECK_REF (p, ref_file, MODE (REF_FILE));
  file = FILE_DEREF (&ref_file);
  CHECK_INIT (p, INITIALISED (file), MODE (FILE));
  open_for_writing (p, ref_file);

  if (elems <= 0) {
    return;
  }
  base_address = DEREF (BYTE_T, &ARRAY (arr));
  elem_index = 0;
  for (k = 0; k < elems; k++) {
    A68_UNION *z = (A68_UNION *) & (base_address[elem_index]);
    MOID_T *mode = (MOID_T *) (VALUE (z));
    BYTE_T *item = (BYTE_T *) & base_address[elem_index + A68_UNION_SIZE];
    if (mode == MODE (PROC_REF_FILE_VOID)) {
      genie_call_proc_ref_file_void (p, ref_file, *(A68_PROCEDURE *) item);
    } else if (mode == MODE (FORMAT)) {
      diagnostic_node (A68_RUNTIME_ERROR, p, ERROR_UNDEFINED_TRANSPUT, MODE (FORMAT));
      exit_genie (p, A68_RUNTIME_ERROR);
    } else if (mode == MODE (SOUND)) {
      write_sound (p, ref_file, (A68_SOUND *) item);
    } else {
      reset_transput_buffer (UNFORMATTED_BUFFER);
      genie_write_standard (p, mode, item, ref_file);
      write_purge_buffer (p, ref_file, UNFORMATTED_BUFFER);
    }
    elem_index += MOID_SIZE (MODE (SIMPLOUT));
  }
}
