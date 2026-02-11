createPackAndRegisterToServerManager(const Server &server, const QString &pathToPackDescription)
{
    Pack p;
    p.fromXmlFile(pathToPackDescription);
    serverManager()->registerPack(server, p);
}
