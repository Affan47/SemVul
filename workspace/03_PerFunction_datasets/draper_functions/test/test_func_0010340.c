toJson(JsonOut *json)
{
    json->propertyStart("idents");
    json->arrayStart();

    for (size_t i = 0; i < idents.dim; i++)
    {   RootObject *ident = idents[i];
        json->item(ident->toChars());
    }

    json->arrayEnd();
}
