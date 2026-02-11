statDescribeGens(void)
{
  nat g, mut, lge, i;
  W_ gen_slop;
  W_ tot_live, tot_slop;
  W_ gen_live, gen_blocks;
  bdescr *bd;
  generation *gen;

  debugBelch(
"----------------------------------------------------------\n"
"  Gen     Max  Mut-list  Blocks    Large     Live     Slop\n"
"       Blocks     Bytes          Objects                  \n"
"----------------------------------------------------------\n");

  tot_live = 0;
  tot_slop = 0;

  for (g = 0; g < RtsFlags.GcFlags.generations; g++) {
      gen = &generations[g];

      for (bd = gen->large_objects, lge = 0; bd; bd = bd->link) {
          lge++;
      }

      gen_live   = genLiveWords(gen);
      gen_blocks = genLiveBlocks(gen);

      mut = 0;
      for (i = 0; i < n_capabilities; i++) {
          mut += countOccupied(capabilities[i].mut_lists[g]);


          bd = capabilities[i].pinned_object_block;
          if (bd != NULL) {
              gen_live   += bd->free - bd->start;
              gen_blocks += bd->blocks;
          }

          gen_live   += gcThreadLiveWords(i,g);
          gen_blocks += gcThreadLiveBlocks(i,g);
      }

      debugBelch("%5d %7" FMT_Word " %9d", g, (W_)gen->max_blocks, mut);

      gen_slop = gen_blocks * BLOCK_SIZE_W - gen_live;

      debugBelch("%8" FMT_Word " %8d %8" FMT_Word " %8" FMT_Word "\n", gen_blocks, lge,
                 gen_live*(W_)sizeof(W_), gen_slop*(W_)sizeof(W_));
      tot_live += gen_live;
      tot_slop += gen_slop;
  }
  debugBelch("----------------------------------------------------------\n");
  debugBelch("%41s%8" FMT_SizeT " %8" FMT_SizeT "\n",
             "",tot_live*sizeof(W_),tot_slop*sizeof(W_));
  debugBelch("----------------------------------------------------------\n");
  debugBelch("\n");
}
