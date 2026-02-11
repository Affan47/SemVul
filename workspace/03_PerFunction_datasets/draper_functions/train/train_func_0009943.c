selectBlockMAC(int *macBytes, int *macRandBytes)
{

    bool addMAC = boolDefaultNo(
            _("Enable block authentication code headers\n"
	"on every block in a file?  This adds about 12 bytes per block\n"
	"to the storage requirements for a file, and significantly affects\n"
	"performance but it also means [almost] any modifications or errors\n"
	"within a block will be caught and will cause a read error."));

    if(addMAC)
	*macBytes = 8;
    else
	*macBytes = 0;


    cout << _("Add random bytes to each block header?\n"
        "This adds a performance penalty, but ensures that blocks\n"
        "have different authentication codes.  Note that you can\n"
        "have the same benefits by enabling per-file initialization\n"
        "vectors, which does not come with as great of performance\n"
        "penalty. \n"
        "Select a number of bytes, from 0 (no random bytes) to 8: ");

    char answer[10];
    int randSize = 0;
    char *res = fgets( answer, sizeof(answer), stdin );
    cout << "\n";

    randSize = (res == 0 ? 0 : atoi( answer ));
    if(randSize < 0)
        randSize = 0;
    if(randSize > 8)
        randSize = 8;

    *macRandBytes = randSize;
}
