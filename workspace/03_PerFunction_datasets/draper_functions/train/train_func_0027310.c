SelectSockets(unsigned long msec )
{

  this->SelectedSocket = 0;

  int max = this->GetNumberOfItems();
  if (max <= 0)
    {
    vtkErrorMacro("No sockets to select.");
    return -1;
    }

  int* socket_indices = new int[max];
  int* sockets_to_select = new int[max];
  int no_of_sockets = 0;

  vtkCollectionIterator* iter = this->NewIterator();

  int index = 0;
  for (iter->InitTraversal(); !iter->IsDoneWithTraversal();
    iter->GoToNextItem(), index++)
    {
    vtkSocket* soc = vtkSocket::SafeDownCast(iter->GetCurrentObject());
    if (!soc->GetConnected())
      {

      continue;
      }
    int sockfd = soc->GetSocketDescriptor();
    sockets_to_select[no_of_sockets] = sockfd;
    socket_indices[no_of_sockets] = index;
    no_of_sockets++;
    }

  if (no_of_sockets == 0)
    {
    vtkErrorMacro("No alive sockets!");
    return -1;
    }
  int res = vtkSocket::SelectSockets(sockets_to_select, no_of_sockets,
    msec, &index);
  int actual_index = -1;
  if (index != -1)
    {
    actual_index = socket_indices[index];
    }

  iter->Delete();
  delete []sockets_to_select;
  delete []socket_indices;

  if (res <= 0 || index == -1)
    {
    return res;
    }

  this->SelectedSocket = vtkSocket::SafeDownCast(
    this->GetItemAsObject(actual_index));
  return 1;
}
