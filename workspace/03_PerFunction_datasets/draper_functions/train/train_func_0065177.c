cli_bytetype_helper(const struct cli_bc *bc, unsigned tid)
{
    unsigned i, j;
    const struct cli_bc_type *ty;

    if (tid & 0x8000) {
        printf("alloc ");
        tid &= 0x7fff;
    }

    if (tid < 65) {
        printf("i%d", tid);
        return;
    }

    i = tid - 65;
    if (i >= bc->num_types) {
        printf("invaltype");
        return;
    }
    ty = &bc->types[i];

    switch (ty->kind) {
    case DFunctionType:
        cli_bytetype_helper(bc, ty->containedTypes[0]);
        printf(" func ( ");
        for (j = 1; j < ty->numElements; ++j) {
            cli_bytetype_helper(bc, ty->containedTypes[0]);
            printf(" ");
        }
        printf(")");
        break;
    case DPointerType:
        cli_bytetype_helper(bc, ty->containedTypes[0]);
        printf("*");
        break;
    case DStructType:
    case DPackedStructType:
        printf("{ ");
        for (j = 0; j < ty->numElements; ++j) {
            cli_bytetype_helper(bc, ty->containedTypes[0]);
            printf(" ");
        }
        printf("}");
        break;
    case DArrayType:
        printf("[");
        printf("%d x ", ty->numElements);
        cli_bytetype_helper(bc, ty->containedTypes[0]);
        printf("]");
        break;
    default:
        printf("unhandled type kind %d, cannot parse", ty->kind);
        break;
    }

}
