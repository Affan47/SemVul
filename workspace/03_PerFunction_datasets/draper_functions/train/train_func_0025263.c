SetCwd(const char *n,const FileAccess::Path &cwd)
{
   ConnectionSlot::SlotValue *s=Find(n);
   if(!s || !s->session)
      return;
   s->session->SetCwd(cwd);
   s->SetValue(s->session->GetConnectURL());
}
