print_k(int code)
{
    switch (BPF_CLASS(code))
    {
    case BPF_LD:
    case BPF_LDX:
        switch (BPF_MODE(code))
        {
        case BPF_ABS:
        case BPF_IND:
        case BPF_MSH:
        case BPF_IMM:
        case BPF_MEM:
            return 1;

        default:
            return 0;
        }

    case BPF_ST:
    case BPF_STX:
        return 1;

    case BPF_JMP:
        if (code == (BPF_JMP | BPF_JA))
            return 1;


    case BPF_ALU:
    case BPF_RET:
        return (BPF_SRC(code) == BPF_K);

    case BPF_MISC:
        return 0;

    default:
        return 0;
    }
}
