cleanupContent()
{
    MeshManager::getSingleton().remove("ground");
    clearScene();
    destroyManagers();
}
