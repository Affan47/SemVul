readFilename() {
    dirent *ent = read();
    if (ent == 0)
        return "";
    return (ent->d_name ? ent->d_name : "");
}
