printJumpStats(const SolveStats& st) const {
	if (st.jumps) {
		const JumpStats& js = *st.jumps;
		w_ += 8;
		printf("\n");
		printKeyValue("Backtracks", "%-6" PRIu64"\n", st.conflicts-st.analyzed);
		printKeyValue("Backjumps", "%-6" PRIu64, st.analyzed);
		printf(" (Bounded: %" PRIu64")\n", js.bJumps);
		printKeyValue("Skippable Levels", "%-6" PRIu64, js.jumpSum);
		printf(" (Skipped: %" PRIu64" Rate: %5.1f%%)\n", js.jumpSum - js.boundSum, percent(js.jumpSum - js.boundSum, js.jumpSum));
		printKeyValue("Max Jump Length", "%-6u", js.maxJump);
		printf(" (Executed: %u)\n", js.maxJumpEx);
		printKeyValue("Max Bound Length", "%-6u\n", js.maxBound);
		printKeyValue("Average Jump Length", "%-6.1f", average(js.jumpSum, st.analyzed));
		printf(" (Executed: %.1f)\n", average(js.jumpSum-js.boundSum, st.analyzed));
		printKeyValue("Average Bound Length", "%-6.1f\n", average(js.boundSum,js.bJumps));
		printKeyValue("Average Model Length", "%-6.1f\n", average(js.modLits,st.models));
		w_ -= 8;
	}
}
