findOrCreate( const char *plainName)
{
    shared_ptr<FileNode> node;
    if(ctx)
	node = ctx->lookupNode( plainName );

    if(!node)
    {
	uint64_t iv = 0;
	string cipherName = naming->encodePath( plainName, &iv );
        node.reset( new FileNode( this, fsConfig,
		plainName,
                (rootDir + cipherName).c_str()));

	if(fsConfig->config->externalIVChaining)
	    node->setName(0, 0, iv);

	rLog(Info, "created FileNode for %s", node->cipherName());
    }

    return node;
}
