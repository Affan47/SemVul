propertyNotify(const XEvent *pEvent_)
{
  Atom wmStateAtom=_server->atom(MSAtomTable::WMState);
  if (pEvent_->xproperty.atom==wmStateAtom) updateWMState();
  else
   {
     Atom workspacePresenceAtom=XInternAtom(display(),"_DT_WORKSPACE_PRESENCE",False);
     if (pEvent_->xproperty.atom==workspacePresenceAtom)
      {
        updateWorkspacePresence();
        updateCurrentWorkspaceState(_server->currentWorkspaceAtom());
      }
   }
}
