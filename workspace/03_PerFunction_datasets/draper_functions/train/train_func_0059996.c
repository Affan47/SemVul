AddLitToFile (int &numFieldsInLiteral, FILE *outRecFile, FILE *outSchemaFile, char *value, Type myType) {


        fprintf (outRecFile, "%s|", value);


        if (myType == Int) {
                fprintf (outSchemaFile, "att%d Int\n", numFieldsInLiteral);
        } else if (myType == Double) {
                fprintf (outSchemaFile, "att%d Double\n", numFieldsInLiteral);
        } else if (myType == String) {
                fprintf (outSchemaFile, "att%d String\n", numFieldsInLiteral);
        } else {
                cerr << "I don't know that type!!\n";
                exit (1);
        }


        numFieldsInLiteral++;
}
