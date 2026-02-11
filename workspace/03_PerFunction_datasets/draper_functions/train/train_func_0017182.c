Xen_hv_check(void)

{
    uint32_t eax, ebx, ecx, edx;
    char signature[13];

    Xen_cpuid(0x40000000, &eax, &ebx, &ecx, &edx);
    *(uint32_t *)(signature + 0) = ebx;
    *(uint32_t *)(signature + 4) = ecx;
    *(uint32_t *)(signature + 8) = edx;
    signature[12] = '\0';

    if ( strcmp("XenVMMXenVMM", signature) || (eax < 0x40000002) )
        return 0;

    Xen_cpuid(0x40000001, &eax, &ebx, &ecx, &edx);
    return 1;
}
