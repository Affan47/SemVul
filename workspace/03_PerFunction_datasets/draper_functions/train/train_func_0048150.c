toJson(JsonOut *json)
{
    json->objectStart();

    jsonProperties(json);

    TypeFunction *tf = (TypeFunction *)type;
    if (tf && tf->ty == Tfunction)
        json->property("parameters", tf->parameters);

    json->property("endline", &endloc);

    if (foverrides.dim)
    {
        json->propertyStart("overrides");
        json->arrayStart();
        for (size_t i = 0; i < foverrides.dim; i++)
        {   FuncDeclaration *fd = foverrides[i];
            json->item(fd->toPrettyChars());
        }
        json->arrayEnd();
    }

    if (fdrequire)
    {
        json->propertyStart("in");
        fdrequire->toJson(json);
    }

    if (fdensure)
    {
        json->propertyStart("out");
        fdensure->toJson(json);
    }

    json->objectEnd();
}
