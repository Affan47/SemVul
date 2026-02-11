GetTileName(wxUint32 tile, bool hexcode) {
    if(tile > TILE_MAX)
        return wxT("");
    wxString name;
    if(hexcode || !IsTileValid(tile)) {
        name << wxT("[") << hexchars[(tile / 16) % 16] << hexchars[tile % 16] << wxT("] ");
    }
    if(tile > TILE_MAX_VALID)
        name << wxT("invalid");
    else
        name << tilenames[tile];
    return name;
}
