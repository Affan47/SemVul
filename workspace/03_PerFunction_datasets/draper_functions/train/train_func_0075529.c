break_SS(SStack* Popcorn)
{
    while(Popcorn->LSize) {
        pop_SS(Popcorn);
    }
    free(Popcorn->Top);
    free(Popcorn);
    return;
}
