render(const FbTk::Texture &texture) {
    if (texture.pixmap().drawable() != 0)
        return renderPixmap(texture);
    else if (texture.type() & FbTk::Texture::PARENTRELATIVE)
        return ParentRelative;
    else if (texture.type() & FbTk::Texture::SOLID)
        return renderSolid(texture);
    else if (texture.type() & FbTk::Texture::GRADIENT) {
        allocateColorTables();
        return renderGradient(texture);
    }

    return None;
}
