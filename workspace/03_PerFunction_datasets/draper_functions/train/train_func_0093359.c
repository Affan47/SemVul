davicom_init_chain(struct nic *nic)
{
  int i;


  for (i=0; i<NTXD; i++) {
    txd[i].buf1addr = (void *)virt_to_bus(&txb[0]);
    txd[i].buf2addr = (void *)virt_to_bus(&txd[i+1]);
    txd[i].buf1sz   = 0;
    txd[i].buf2sz   = 0;
    txd[i].control  = 0x184;
    txd[i].status   = 0x00000000;
  }


  for (i=0; i<192; i++) txb[i] = 0xFF;
  txb[0] = nic->node_addr[0];
  txb[1] = nic->node_addr[1];
  txb[4] = nic->node_addr[2];
  txb[5] = nic->node_addr[3];
  txb[8] = nic->node_addr[4];
  txb[9] = nic->node_addr[5];


  for (i=0; i<NRXD; i++) {
    rxd[i].buf1addr = (void *)virt_to_bus(&rxb[i * BUFLEN]);
    rxd[i].buf2addr = (void *)virt_to_bus(&rxd[i+1]);
    rxd[i].buf1sz   = BUFLEN;
    rxd[i].buf2sz   = 0;
    rxd[i].control  = 0x4;
    rxd[i].status   = 0x80000000;
  }


  txd[NTXD - 1].buf2addr = (void *)virt_to_bus(&txd[0]);
  rxd[NRXD - 1].buf2addr = (void *)virt_to_bus(&rxd[0]);
  TxPtr = 0;
  rxd_tail = 0;
}
