sync (UpdateRequired sync_required)
{
  bool none_required = ( !sync_required.remote &&
                         !sync_required.local &&
                         !sync_required.extended );

  if (rxWindow && (sync_required.remote || none_required)) {
    rxWindow->Sync();
  }

  if (lxWindow && (sync_required.local || none_required)) {
    lxWindow->Sync();
  }

  if (exWindow && (sync_required.extended || none_required)) {
    exWindow->Sync();
  }
}
