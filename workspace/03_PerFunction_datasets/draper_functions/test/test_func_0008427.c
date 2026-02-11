show_tree(assembly_operand AO, int annotate)
{   if (AO.type == EXPRESSION_OT) show_node(AO.value, 0, annotate);
    else
    {   printf("Constant: "); print_operand(AO);
        if (annotate && (AO.marker != 0))
            printf(" [%s]", describe_mv(AO.marker));
        printf("\n");
    }
}
