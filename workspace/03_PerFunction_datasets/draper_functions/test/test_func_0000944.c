hoz_nopath(const char *file)
{
    const char *aux;
    aux = (file + strlen(file));
    while (*aux != HOZ_PATHSEP) {
        if (aux == file) {
            return aux;
        }
        aux--;
    }
    return aux + 1;
}
