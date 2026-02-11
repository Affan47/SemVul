operation_new (GoaKerberosIdentityManager *self,
               GCancellable               *cancellable,
               OperationType               type,
               GSimpleAsyncResult         *result)
{
  Operation *operation;

  operation = g_slice_new (Operation);

  operation->manager = self;
  operation->type = type;

  if (cancellable == NULL)
    cancellable = g_cancellable_new ();
  else
    g_object_ref (cancellable);
  operation->cancellable = cancellable;

  if (result != NULL)
    g_object_ref (result);
  operation->result = result;

  operation->identity = NULL;

  return operation;
}
