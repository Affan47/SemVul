print()
{
    int i;

    if (way_ < 0) {
        printf("Down Fix ");
        for (i = 0; i < numberDown_; i++) {
            int iColumn = downList_[i];
            printf("%d ", iColumn);
        }
    } else {
        printf("Up Fix ");
        for (i = 0; i < numberUp_; i++) {
            int iColumn = upList_[i];
            printf("%d ", iColumn);
        }
    }
    printf("\n");
}
