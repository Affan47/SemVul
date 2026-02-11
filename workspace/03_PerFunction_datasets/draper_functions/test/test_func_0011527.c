needsInstall()
{
    if (getLastInstalled() == 0 || getLastCompiled() == 0)
    {
        return true;
    }
    return !(getLastModified() <= getLastCompiled() &&
             getLastCompiled() <= getLastInstalled());
}
