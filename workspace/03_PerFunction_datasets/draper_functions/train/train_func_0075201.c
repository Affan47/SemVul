directLookup( const char *path )
{
    return shared_ptr<FileNode>(
            new FileNode( this,
                fsConfig,
                "unknown", path ));
}
