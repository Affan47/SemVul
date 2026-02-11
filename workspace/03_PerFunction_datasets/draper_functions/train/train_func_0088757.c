main(int argc, char **argv)
{
    JsonListNode *root = jsonListCreate(jsonCreateInteger("hallo",100));
    JsonListNode *curr = jsonListAdd(root,jsonCreateInteger("h",22));
    for(int i = 0; i < 10; i++)
    {
        curr = jsonListAdd(curr,jsonCreateInteger("H",i));
    }

    jsonListForeach(root,&printNode);
    jsonListClear(root);

    return 0;
}
