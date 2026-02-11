setBreakpoint(int file, int line) {
    int i = breakpointIndex(file, line);

    if (i != -1)
        printf("Breakpoint already set at %s:%d\n", sourceFileName(file), line);
    else {
        i = availableBreakpointSlot();
        if (i == -1)
            printf("No room for more breakpoints. Delete one first.\n");
        else {
            int lineIndex = findSourceLineIndex(pointerTo(header->sourceLineTable), file, line);
            SourceLineEntry *entry = pointerTo(header->sourceLineTable);
            char leadingText[100] = "Breakpoint";
            if (entry[lineIndex].file == EOF) {
                printf("Line %d not available\n", line);
            } else {
                if (entry[lineIndex].line != line)
                    sprintf(leadingText, "Line %d not available, breakpoint instead", line);
                breakpoint[i].file = entry[lineIndex].file;
                breakpoint[i].line = entry[lineIndex].line;
                printf("%s set at %s:%d\n", leadingText, sourceFileName(entry[lineIndex].file), entry[lineIndex].line);
                showSourceLine(entry[lineIndex].file, entry[lineIndex].line);
                printf("\n");
            }
        }
    }
}
