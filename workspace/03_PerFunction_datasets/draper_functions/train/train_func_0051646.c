imms_magic_preprocess_path(string &path)
{
    path = string_tolower(path);
    path = rex.replace(path, "[-\\s_\\.]{2,}", "/", Regexx::global);
    path = rex.replace(path, "(/|^)[\\(\\[]", "/", Regexx::global);
    path = rex.replace(path, "[\\(\\[][^/]+[\\)\\]]/", "/", Regexx::global);
    path = rex.replace(path, "[-\\s_\\./][iv]{2}i?[/$]", "/", Regexx::global);
    path = rex.replace(path, "[^a-z/]", "", Regexx::global);
}
