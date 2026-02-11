knowledge_monster_face(sstring code) {
    const archetype *monster = find_archetype(code);

    if (!monster || monster->clone.face == blank_face || monster->clone.face == NULL)
        return (unsigned)-1;

    return monster->clone.face->number;
}
