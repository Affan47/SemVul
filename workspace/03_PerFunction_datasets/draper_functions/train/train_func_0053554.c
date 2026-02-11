isVertical() const {
    return (placement() == RIGHTCENTER ||
            placement() == RIGHTTOP ||
            placement() == RIGHTBOTTOM ||
            placement() == LEFTCENTER ||
            placement() == LEFTTOP ||
            placement() == LEFTBOTTOM);
}
