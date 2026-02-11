makeInputSource(DssslSpecEventHandler &eh,
				     Owner<InputSource> &in)
{
  const InternalEntity *internal = entity_->asInternalEntity();
  if (internal) {
    in = new InternalInputSource(internal->string(),
			         EntityOrigin::make(entity_, Location()));
    return;
  }
  const StringC &sysid
    = entity_->asExternalEntity()->externalId().effectiveSystemId();
  if (sysid.size())
    in = eh.parser_->entityManager().open(sysid, *eh.charset_, InputSourceOrigin::make(),
					  0, *eh.mgr_);
}
