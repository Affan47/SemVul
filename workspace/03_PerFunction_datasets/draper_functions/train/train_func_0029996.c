load(const std::string& filename) {
    beforeRead();
    TextInput::Settings settings;
    getDeserializeSettings(settings);

    TextInput ti(FileSystem::resolve(filename), settings);
    deserialize(ti);
}
