addSound(const std::string &name, const Path &file)
{
    Mix_Chunk *chunk = loadSound(file);
    if (chunk) {
        addRes(name, chunk);
    }
}
