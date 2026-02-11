InfHostFindOrAddSection(HINF InfHandle,
                        const WCHAR *Section,
                        PINFCONTEXT *Context)
{
  INFSTATUS Status;

  Status = InfpFindOrAddSection((PINFCACHE) InfHandle, Section, Context);
  if (INF_SUCCESS(Status))
    {
      return 0;
    }
  else
    {
      errno = Status;
      return -1;
    }
}
