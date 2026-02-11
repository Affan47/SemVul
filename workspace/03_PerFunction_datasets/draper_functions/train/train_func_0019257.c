needsCompile()
{
    return getLastModified()>getLastCompiled() || getLastCompiled()==0;
}
