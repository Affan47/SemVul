do_identity_inquiry (Operation *operation)
{
  if (operation->inquiry_func == NULL)
    {
      return;
    }

  operation->inquiry_func (operation->inquiry,
                           operation->cancellable,
                           operation->inquiry_data);
}
