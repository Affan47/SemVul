g_daemon_file_output_stream_write_async  (GOutputStream      *stream,
					  const void         *buffer,
					  gsize               count,
					  int                 io_priority,
					  GCancellable       *cancellable,
					  GAsyncReadyCallback callback,
					  gpointer            data)
{
  GDaemonFileOutputStream *file;
  WriteOperation *op;

  file = G_DAEMON_FILE_OUTPUT_STREAM (stream);


  if (count > MAX_WRITE_SIZE)
    count = MAX_WRITE_SIZE;

  op = g_new0 (WriteOperation, 1);
  op->state = WRITE_STATE_INIT;
  op->buffer = buffer;
  op->buffer_size = count;

  run_async_state_machine (file,
			   (state_machine_iterator)iterate_write_state_machine,
			   op,
			   io_priority,
			   callback, data,
			   cancellable,
			   async_write_done);
}
